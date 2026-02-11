callback()
{

  Dprintf((" usart module RCREG time:0x%"PRINTF_GINT64_MODIFIER"x=%"PRINTF_GINT64_MODIFIER"d\n", get_cycles().get(), get_cycles().get()));


  switch(receive_state) {
  case RS_WAITING_FOR_START:
    Dprintf(("waiting for start\n"));
    break;

  case RS_START_BIT:
     if (bIsLow(m_cLastRXState))
     {
        receive_state = RS_RECEIVING;
        rx_count = bits_per_byte + use_parity;
        rx_byte = 0;
        future_time = get_cycles().get() + time_per_bit;

        if(!autobaud)
          get_cycles().set_break(future_time, this);

     }
     else
     {
       receive_state = RS_WAITING_FOR_START;
     }
     break;

  case RS_RECEIVING:

    if (rx_count--)
    {
        rx_byte = (rx_byte >> 1) | (bIsHigh(m_cLastRXState) ?
                1<<(bits_per_byte-1) : 0);
        future_time = get_cycles().get() + time_per_bit;

        if(!autobaud)
          get_cycles().set_break(future_time, this);
    }
    else if (bIsHigh(m_cLastRXState))
    {
        m_usart->newRxByte(rx_byte);
        m_usart->show_tx(rx_byte);
        receive_state = RS_WAITING_FOR_START;
    }
    else
    {
        cout << "USART module RX overrun error\n";
        receive_state = RS_WAITING_FOR_START;
    }

    break;
  case RS_STOPPED:
    receive_state = RS_WAITING_FOR_START;
    cout << "received a stop bit\n";
    break;
  default:
    break;
  }


}
