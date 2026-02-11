OnAudioMonitor(Call* call, const AudioInfo& info) {
  std::map<uint32, int> active_ssrc_to_level_map;
  cricket::AudioInfo::StreamList::const_iterator stream_list_it;
  for (stream_list_it = info.active_streams.begin();
       stream_list_it != info.active_streams.end(); ++stream_list_it) {
    uint32 ssrc = stream_list_it->first;
    active_ssrc_to_level_map[ssrc] = stream_list_it->second;


    if (ssrc_to_speaking_state_map_.find(ssrc) ==
        ssrc_to_speaking_state_map_.end()) {
      ssrc_to_speaking_state_map_[ssrc] = SS_NOT_SPEAKING;
    }
  }

  int max_level = 0;
  uint32 loudest_speaker_ssrc = 0;


  std::map<uint32, SpeakingState>::iterator state_it;
  for (state_it = ssrc_to_speaking_state_map_.begin();
       state_it != ssrc_to_speaking_state_map_.end(); ++state_it) {
    bool is_previous_speaker = current_speaker_ssrc_ == state_it->first;


    std::map<uint32, int>::const_iterator level_it =
        active_ssrc_to_level_map.find(state_it->first);


    int level = (level_it != active_ssrc_to_level_map.end()) ?
        level_it->second : 0;
    switch (state_it->second) {
      case SS_NOT_SPEAKING:
        if (level > 0) {

          level = 0;
          state_it->second = SS_MIGHT_BE_SPEAKING;
        } else {

        }
        break;
      case SS_MIGHT_BE_SPEAKING:
        if (level > 0) {
          state_it->second = SS_SPEAKING;
        } else {
          state_it->second = SS_NOT_SPEAKING;
        }
        break;
      case SS_SPEAKING:
        if (level > 0) {

        } else {
          state_it->second = SS_WAS_SPEAKING_RECENTLY1;
          if (is_previous_speaker) {


            level = kMaxAudioLevel;
          }
        }
        break;
      case SS_WAS_SPEAKING_RECENTLY1:
        if (level > 0) {
          state_it->second = SS_SPEAKING;
        } else {
          state_it->second = SS_WAS_SPEAKING_RECENTLY2;
          if (is_previous_speaker) {


            level = kMaxAudioLevel;
          }
        }
        break;
      case SS_WAS_SPEAKING_RECENTLY2:
        if (level > 0) {
          state_it->second = SS_SPEAKING;
        } else {
          state_it->second = SS_NOT_SPEAKING;
        }
        break;
    }

    if (level > max_level) {
      loudest_speaker_ssrc = state_it->first;
      max_level = level;
    } else if (level > 0 && level == max_level && is_previous_speaker) {

      loudest_speaker_ssrc = state_it->first;
    }
  }


  uint32 now = talk_base::Time();
  if (earliest_permitted_switch_time_ <= now &&
      current_speaker_ssrc_ != loudest_speaker_ssrc) {
    current_speaker_ssrc_ = loudest_speaker_ssrc;
    LOG(LS_INFO) << "Current speaker changed to " << current_speaker_ssrc_;
    earliest_permitted_switch_time_ = now + min_time_between_switches_;
    SignalUpdate(this, current_speaker_ssrc_);
  }
}
