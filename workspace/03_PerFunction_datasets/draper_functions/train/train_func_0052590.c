KeepPart(Prefilter* prefilter, int level) {
  if (prefilter == NULL)
    return false;

  switch (prefilter->op()) {
    default:
      LOG(DFATAL) << "Unexpected op in KeepPart: "
                  << prefilter->op();
      return false;

    case Prefilter::ALL:
      return false;

    case Prefilter::ATOM:
      return prefilter->atom().size() >=
          static_cast<size_t>(FLAGS_filtered_re2_min_atom_len);

    case Prefilter::AND: {
      int j = 0;
      vector<Prefilter*>* subs = prefilter->subs();
      for (size_t i = 0; i < subs->size(); i++)
        if (KeepPart((*subs)[i], level + 1))
          (*subs)[j++] = (*subs)[i];
        else
          delete (*subs)[i];

      subs->resize(j);
      return j > 0;
    }

    case Prefilter::OR:
      for (size_t i = 0; i < prefilter->subs()->size(); i++)
        if (!KeepPart((*prefilter->subs())[i], level + 1))
          return false;
      return true;
  }
}
