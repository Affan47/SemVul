operator<< (PVR_TIMER& lhs, const Timer& rhs) {
	memset(&lhs, 0, sizeof(lhs));

	lhs.bIsRepeating = rhs.IsRepeating;
	lhs.endTime = rhs.EndTime;
	lhs.firstDay = rhs.FirstDay;
	lhs.iClientChannelUid = rhs.ChannelUID;
	lhs.iClientIndex = rhs.Index;
	lhs.iEpgUid = rhs.EpgUID;
	lhs.iLifetime = rhs.LifeTime;
	lhs.iMarginEnd = 0;
	lhs.iMarginStart = 0;
	lhs.iPriority = rhs.Priority;
	lhs.iWeekdays = rhs.WeekDays;
	lhs.startTime = rhs.StartTime;

  lhs.state = PVR_TIMER_STATE_CANCELLED;

  if(rhs.State & 8) {
    lhs.state = PVR_TIMER_STATE_RECORDING;
  }
  else if(rhs.State & 2048) {
    lhs.state = PVR_TIMER_STATE_CONFLICT_NOK;
  }
  else if(rhs.State & 1024) {
    lhs.state = PVR_TIMER_STATE_CONFLICT_OK;
  }
  else if(rhs.State & 1) {
    lhs.state = PVR_TIMER_STATE_SCHEDULED;
  }

	strncpy(lhs.strDirectory, rhs.Directory.c_str(), sizeof(lhs.strDirectory));
	strncpy(lhs.strSummary, rhs.Summary.c_str(), sizeof(lhs.strSummary));
	strncpy(lhs.strTitle, rhs.Title.c_str(), sizeof(lhs.strTitle));

	return lhs;
}
