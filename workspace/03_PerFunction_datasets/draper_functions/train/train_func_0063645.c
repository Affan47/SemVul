find_similar_event(list<NetEvent*>&event_list)
{
      if (probes_ == 0)
	    return;

      set<NetEvent*> event_candidates;
      list<NetEvProbe*>first_probes;
      probes_->find_similar_probes(first_probes);

      for (list<NetEvProbe*>::iterator idx = first_probes.begin()
		 ; idx != first_probes.end() ; idx ++) {
	    event_candidates .insert( (*idx)->event() );
      }

      for (set<NetEvent*>::iterator idx = event_candidates.begin()
		 ; idx != event_candidates.end() ; idx ++) {
	    if (this == *idx)
		  continue;
	    if (scope()->is_auto() && (scope() != (*idx)->scope()))
		  continue;
	    if (events_are_similar(this, *idx))
		  event_list.push_back(*idx);
      }

}
