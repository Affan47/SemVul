report_eval(double f)
{
  if (num_evaluations_ == 0) {
    start_error_ = f;
    end_error_ = f;
  }
  if (f < end_error_)
    end_error_ = f;

  ++num_evaluations_;
}
