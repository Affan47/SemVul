CalculateIncreases() {


  rtp_seq_num_increase_ = prev_rtp_seq_num_ - first_rtp_seq_num_ + 1;


  elapsed_time_increases_ = packet_count_ <= 1 ? kDefaultTimeIncrease :
      (prev_elapsed_time_ - first_elapsed_time_) * packet_count_ /
      (packet_count_ - 1);
  rtp_timestamp_increase_ = frame_count_ <= 1 ? kDefaultTimeIncrease :
      (prev_rtp_timestamp_ - first_rtp_timestamp_) * frame_count_ /
      (frame_count_ - 1);
}
