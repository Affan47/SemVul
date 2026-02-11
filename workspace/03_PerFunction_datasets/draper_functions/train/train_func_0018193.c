main(int argc, char **argv) {
  namespace s = fst::script;
  using fst::script::FstClass;

  string usage = "Finds shortest distance(s) in an FST.\n\n  Usage: ";
  usage += argv[0];
  usage += " [in.fst [distance.txt]]\n";

  std::set_new_handler(FailedNewHandler);
  SET_FLAGS(usage.c_str(), &argc, &argv, true);
  if (argc > 3) {
    ShowUsage();
    return 1;
  }

  string in_fname = (argc > 1 && (strcmp(argv[1], "-") != 0)) ? argv[1] : "";
  string out_fname = argc > 2 ? argv[2] : "";

  FstClass *ifst = FstClass::Read(in_fname);
  if (!ifst) return 1;

  vector<s::WeightClass> distance;

  fst::QueueType qt;

  if (FLAGS_queue_type == "auto") {
    qt = fst::AUTO_QUEUE;
  } else if (FLAGS_queue_type == "fifo") {
    qt = fst::FIFO_QUEUE;
  } else if (FLAGS_queue_type == "lifo") {
    qt = fst::LIFO_QUEUE;
  } else if (FLAGS_queue_type == "shortest") {
    qt = fst::SHORTEST_FIRST_QUEUE;
  } else if (FLAGS_queue_type == "state") {
    qt = fst::STATE_ORDER_QUEUE;
  } else if (FLAGS_queue_type == "top") {
    qt = fst::TOP_ORDER_QUEUE;
  } else {
    LOG(ERROR) << "Unknown or unsupported queue type: " << FLAGS_queue_type;
    return 1;
  }

  if (FLAGS_reverse && qt != fst::AUTO_QUEUE) {
    LOG(ERROR) << "Specifying a non-default queue with reverse not supported.";
    return 1;
  }

  if (FLAGS_reverse) {
    s::ShortestDistance(*ifst, &distance, FLAGS_reverse, FLAGS_delta);
  } else {
    s::ShortestDistanceOptions opts(qt, s::ANY_ARC_FILTER,
                                    FLAGS_nstate, FLAGS_delta);
    s::ShortestDistance(*ifst, &distance, opts);
  }

  s::WritePotentials(out_fname, distance);

  return 0;
}
