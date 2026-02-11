Hide_Ambiguities(allseq *data)
{
  int i;

  For(i,data->crunch_len)
    {
      if(data->ambigu[i])
	{
	  data->wght[i] = 0.0;
	}
    }
}
