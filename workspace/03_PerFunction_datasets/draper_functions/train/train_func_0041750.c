next_minute(struct icalrecur_iterator_impl* impl)
{

  short has_by_data = (impl->by_ptrs[BY_MINUTE][0]!=ICAL_RECURRENCE_ARRAY_MAX);
  short this_frequency = (impl->rule.freq == ICAL_MINUTELY_RECURRENCE);

  short end_of_data = 0;

  assert(has_by_data || this_frequency);


  if (next_second(impl) == 0){
      return 0;
  }

  if(  has_by_data ){


      impl->by_indices[BY_MINUTE]++;

      if (impl->by_ptrs[BY_MINUTE][impl->by_indices[BY_MINUTE]]
	  ==ICAL_RECURRENCE_ARRAY_MAX){

	  impl->by_indices[BY_MINUTE] = 0;

	  end_of_data = 1;
      }

      impl->last.minute =
	  impl->by_ptrs[BY_MINUTE][impl->by_indices[BY_MINUTE]];

  } else if( !has_by_data &&  this_frequency ){

      increment_minute(impl,impl->rule.interval);
  }


  if(has_by_data && end_of_data && this_frequency ){
      increment_hour(impl,1);
  }

  return end_of_data;
}
