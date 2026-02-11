DataCallback(Serial &ser, Data *data)
{
	ddout("Serial::DataCallback called");

	if( data->GetSize() <= 4 )
		return;


	if( ser.m_callback ) {
		(*ser.m_callback)(ser.m_callback_context,
			data->GetData() + 4,
			data->GetSize() - 4);
	}


}
