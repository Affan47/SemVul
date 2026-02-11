evaluate_models()
{
  ::status.evaluate.start();
  if (OPT::bypass) {
    converged = true;
    swap(_sim->_evalq, _sim->_evalq_uc);
    while (!_sim->_evalq->empty()) {
      converged &= _sim->_evalq->front()->do_tr();
      _sim->_evalq->pop_front();
    }
  }else{
    _sim->_evalq_uc->clear();
    converged = CARD_LIST::card_list.do_tr();
  }
  while (!_sim->_late_evalq.empty()) {
    converged &= _sim->_late_evalq.front()->do_tr_last();
    _sim->_late_evalq.pop_front();
  }
  ::status.evaluate.stop();
}
