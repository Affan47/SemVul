main (int argc, char** argv) {

  if (argc > 1) {
    run_tests();
  }
  else {
    t_box_list box_list;
    if (!read_boxes(box_list)) {
      std::cerr << "Unable to read the box list!" << std::endl;
      exit(1);
    }
    run_packer(box_list);
  }
  return 0;
}
