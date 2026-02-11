DecryptData( CSSLObject * SSLObject, CString s )
{
	CString res;
	CByteArray bain,baout;
	int i,tmplen;
	EVP_CIPHER_CTX ctx;


	if ( !SSLObject || (s.IsEmpty()) )
	{
		return res;
	}

	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit(&ctx, EVP_bf_cbc(), SSLObject->m_localkey, SSLObject->m_localiv);

	bain.SetSize(0);
	bain.Append(s.Data(),s.Length());

	if ( CBase64::Decode(&baout,&bain) > 0 )
	{
		bain.SetSize( baout.Size() + ( 2 * EVP_CIPHER_CTX_block_size(&ctx) ) );

		i = 0;

		if ( EVP_DecryptUpdate(&ctx, bain.Data(), &i, baout.Data(), (int)baout.Size() ) )
		{
			tmplen = 0;
			if ( EVP_DecryptFinal(&ctx, bain.Data()+i, &tmplen) )
			{
				i+=tmplen;
				res.Set((const char*)bain.Data()+2,i-2);
			}
		}
	}

	EVP_CIPHER_CTX_cleanup(&ctx);

	return res;
}
