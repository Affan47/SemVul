dump_profile_counters(void)
{
  std::cerr << "(audioio-db-server) *** profile begin ***" << std::endl;
  std::cerr << "Profile_full_rep: " << impl_repp->profile_full_rep << std::endl;
  std::cerr << "Profile_no_processing_rep: " << impl_repp->profile_no_processing_rep << std::endl;
  std::cerr << "Profile_not_full_anymore_rep: " << impl_repp->profile_not_full_anymore_rep << std::endl;
  std::cerr << "Profile_processing_rep: " << impl_repp->profile_processing_rep << std::endl;
  std::cerr << "Profile_read_xrun_danger_rep: " << impl_repp->profile_read_xrun_danger_rep << std::endl;
  std::cerr << "Profile_write_xrun_danger_rep: " << impl_repp->profile_write_xrun_danger_rep << std::endl;
  std::cerr << "Profile_rounds_total_rep: " << impl_repp->profile_rounds_total_rep << std::endl;
  std::cerr << "Fastest/slowest/average loop time: ";
  std::cerr << kvu_numtostr(impl_repp->looptimer_rep.min_duration_seconds() * 1000, 1);
  std::cerr << "/";
  std::cerr << kvu_numtostr(impl_repp->looptimer_rep.max_duration_seconds() * 1000, 1);
  std::cerr << "/";
  std::cerr << kvu_numtostr(impl_repp->looptimer_rep.average_duration_seconds() * 1000, 1);
  std::cerr << " msec." << std::endl;
  std::cerr << "(audioio-db-server) *** profile end   ***" << std::endl;
}
