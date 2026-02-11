reinit_chains(bool force)
{
  for(size_t i = 0; i != chains_repp->size(); i++) {
    if (force == true ||
        (*chains_repp)[i]->is_initialized() != true) {
      (*chains_repp)[i]->init(0, 0, 0);
    }
  }
}
