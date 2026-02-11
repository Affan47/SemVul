init(void)
{
  MESSAGE_ITEM otemp;
  otemp << "Sine oscillator created; frequency ";
  otemp.setprecision(3);
  otemp << frequency();
  otemp << " and initial phase of ";
  otemp << phase_offset() << ".";
  ECA_LOG_MSG(ECA_LOGGER::user_objects, otemp.to_string());
}
