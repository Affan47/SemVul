readAllKeys ()
  {
    makeThisCurrent();
    int status(0);
    int n (0);
    int dum(0);
    if (fits_get_hdrpos(fitsPointer(),&n,&dum,&status)) throw FitsError(status);

    for (int j = 1; j <= n; ++j)
    {


       try
       {


          std::auto_ptr<Keyword> key(KeywordCreator::getKeyword(j,this));

          if (key.get() != 0)
          {
              int keyClass = fits_get_keyclass(const_cast<char*>(key->name().c_str()));
              for (size_t i=0; i<s_nCategories; ++i)
              {
                 if (keyClass == s_iKeywordCategories[i])
                 {
                    saveReadKeyword(key.get());
                    break;
                 }
              }
          }
       }
       catch (FitsError& )
       {
       }
    }

    getHistory();
    getComments();
  }
