run(const SWFCxForm& cx, const SWFMatrix& )
{


  typedef std::deque<UnivocalPath> UniPathList;

  std::vector<UniPathList> unipathvec(_num_styles);

  for (size_t i = 0; i < _paths.size(); ++i) {

    if (_paths[i].empty()) {
      continue;
    }

    int leftfill = _paths[i].getLeftFill();
    if (leftfill) {
      unipathvec[leftfill-1].push_front(UnivocalPath(&_paths[i], UnivocalPath::FILL_LEFT));
    }

    int rightfill = _paths[i].getRightFill();
    if (rightfill) {
      unipathvec[rightfill-1].push_front(UnivocalPath(&_paths[i], UnivocalPath::FILL_RIGHT));
    }
  }

  for (size_t i = 0; i < _num_styles; ++i) {

    start_shapes(i+1, cx);
    UniPathList& path_list = unipathvec[i];

    while (!path_list.empty()) {

      if (closed_shape()) {
        reset_shape(path_list.front());
        path_list.pop_front();
      }

      UniPathList::iterator it = emitConnecting(path_list);

      if (it == path_list.end()) {
        if (!closed_shape()) {
            log_error(_("path not closed!"));
          _cur_endpoint = _shape_origin;
        }
      } else {
        path_list.erase(it);
      }

    }
    end_shapes(i+1);
  }

}
