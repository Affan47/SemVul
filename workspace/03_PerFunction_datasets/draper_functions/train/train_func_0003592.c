GetToken()
{
   if(!my_token || token_timer.Stopped()) {

      my_last_token.set(my_token);
      my_token.truncate();
      for(int i=0; i<16; i++)
	 my_token.append(char(random()/13));
      token_timer.Reset();
   }
   return my_token;
}
