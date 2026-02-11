ResetParams() {
  offer_params_.clear();
  state_ = ST_INIT;
  LOG(LS_INFO) << "SRTP reset to init state";
  return true;
}
