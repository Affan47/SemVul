Encode( int c, CString & d )
{

	switch(c&0xFF)
	{
		case 126:
			d.Append("/%DCN126%/");
			break;
		case 124:
			d.Append("/%DCN124%/");
			break;
		case 96:
			d.Append("/%DCN096%/");
			break;
		case 36:
			d.Append("/%DCN036%/");
			break;
		case 5:
			d.Append("/%DCN005%/");
			break;
		case 0:
			d.Append("/%DCN000%/");
			break;
		default:
			d.Append((char)c);
			break;
	}
}
