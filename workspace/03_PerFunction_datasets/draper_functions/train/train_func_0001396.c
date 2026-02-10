getNumPoints(uint64_t max_id) const {
    size_t retval = 0;

    for (ScanGraph::const_iterator it = this->begin(); it != this->end(); it++) {
      retval += (*it)->scan->size();
      if ((max_id > 0) && ((*it)->id == max_id)) break;
    }
    return retval;
  }
