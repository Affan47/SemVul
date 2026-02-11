replace_type(string *arc_labeling, char *binname,
                                       string errmsg, bool epsilon_on_replace) {
  fst::ReplaceLabelType replace_label_type;
  if ((*arc_labeling) == "neither" || epsilon_on_replace) {
    replace_label_type = fst::REPLACE_LABEL_NEITHER;
  } else if ((*arc_labeling) == "input") {
    replace_label_type = fst::REPLACE_LABEL_INPUT;
  } else if ((*arc_labeling) == "output") {
    replace_label_type = fst::REPLACE_LABEL_OUTPUT;
  } else if ((*arc_labeling) == "both") {
    replace_label_type = fst::REPLACE_LABEL_BOTH;
  } else {
    LOG(ERROR) << binname << errmsg
               << "arc labeling option: " << (*arc_labeling);
    exit(1);
  }
  return replace_label_type;
}
