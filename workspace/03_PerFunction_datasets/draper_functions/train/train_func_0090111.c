get_next_available_row_with_add_if_necessary()
{
  Gtk::TreeModel::iterator result;

  if(!m_refListStore)
    return result;

  bool bPreventUserSignals = get_prevent_user_signals();
  set_prevent_user_signals(true);

  if(get_allow_user_actions())
  {
    Gtk::TreeModel::iterator iter = get_last_row();

    if(iter != get_model()->children().end())
    {

      if( get_is_placeholder_row(iter))
      {
        result = iter;
      }
      else
      {

        result = m_refListStore->append();
      }
    }
    else
    {

       result = m_refListStore->append();
    }
  }
  else
  {
     result = m_refListStore->append();
  }

  set_prevent_user_signals(bPreventUserSignals);

  return result;
}
