init(string category, string id, TreeHandler* config)
{
  ModWidget::init(category, id, config);


  this->min = m_pConfig->getMin(this->category, this->id_string);
  this->max = m_pConfig->getMax(this->category, this->id_string);

  this->def = this->min;


  this->set_increments(1, 10);


  this->set_digits(m_pConfig->getFractionalDigits(this->category, this->id_string));


  this->set_draw_value(true);


  this->set_range(this->min, this->max);


  this->reload();
}
