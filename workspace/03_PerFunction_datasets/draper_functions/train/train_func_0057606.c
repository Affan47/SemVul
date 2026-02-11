invoke()
{
  list <string> :: iterator si;

  start_new_input_stream();

  if(body.size()) {

    for(si = body.begin();
	si != body.end();
	++si)
      add_string_to_input_buffer( (*si).c_str(), this);
  }

  add_string_to_input_buffer("endm\n", this);

}
