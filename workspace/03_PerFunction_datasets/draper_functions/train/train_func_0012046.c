UnEscapeSpecials( const CString & s )
{
	int i,i1;
	CString res;
	CString temp;
	CString four,six;

	for(i=0;i<s.Length();i++)
	{
		if ( s.Data()[i] == '&' )
		{
			if ( s.Mid(i,2) == "&#" )
			{
				if ( (i1 = s.Find(';',i)) != -1 )
				{
					if ( (i1-i) <= 5 )
					{
						temp = s.Mid(i,i1-i);


						temp = temp.Mid(2);

						if ( temp.Left(1) == "x" )
						{
							temp = temp.Mid(1);

							res += temp.asINT(16);
						}
						else
						{
							res += temp.asINT();
						}


						i += i1-i;
						continue;
					}
				}
			}
			else
			{
				four = s.Mid(i,4);
				if ( four == "&lt;" )
				{
					res += '<';
					i += 3;
					continue;
				}
				else if ( four == "&gt;" )
				{
					res += '>';
					i += 3;
					continue;
				}
				else
				{
					if ( s.Mid(i,5) == "&amp;" )
					{
						res += '&';
						i += 4;
						continue;
					}
					else
					{
						six = s.Mid(i,6);
						if ( six == "&apos;" )
						{
							res += '\'';
							i += 5;
							continue;
						}
						else if ( six == "&quot;" )
						{
							res += '"';
							i += 5;
							continue;
						}
					}
				}
			}
		}

		res += s.Data()[i];
	}


	return res;
}
