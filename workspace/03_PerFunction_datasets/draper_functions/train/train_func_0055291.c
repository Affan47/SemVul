ProgressReport(bool force) {
  const int kProgressReportGranularity = 10000;
  if (control_ != NULL
      && (force || progress_counter_ % kProgressReportGranularity == 0)) {
      return
          control_->ReportProgressValue(progress_counter_, progress_total_) ==
          v8::ActivityControl::kContinue;
  }
  return true;
}
