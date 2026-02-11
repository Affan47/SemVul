Sample(uint32 sample_time, int bandwidth) {
  if (bandwidth < 0) {
    return false;
  }

  accumulator_.AddSample(bandwidth);


  bandwidth = accumulator_.ComputeMean();

  if (bandwidth < bandwidth_estimation_) {
    time_at_last_change_ = sample_time;
    bandwidth_estimation_ = bandwidth;
    return true;
  }

  const int old_bandwidth_estimation = bandwidth_estimation_;
  const double increase_threshold_d = percent_increase_ * bandwidth_estimation_;
  if (increase_threshold_d > INT_MAX) {

    return false;
  }

  const int increase_threshold = static_cast<int>(increase_threshold_d);
  if (bandwidth < increase_threshold) {
    time_at_last_change_ = sample_time;


  } else if (sample_time >= time_at_last_change_ + time_between_increase_) {
    time_at_last_change_ = sample_time;
    if (increase_threshold == 0) {
      bandwidth_estimation_ = bandwidth / 2;
    } else {
      bandwidth_estimation_ = increase_threshold;
    }
  }


  return old_bandwidth_estimation != bandwidth_estimation_;
}

}
