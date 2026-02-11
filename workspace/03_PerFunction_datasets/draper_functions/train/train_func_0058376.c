Read(OBBase* pOb, std::istream* pin)
  {
    if(pin) {
      pInStream=pin;
      CheckedForGzip = false;
    }

    if(!pInFormat || !pInStream) return false;

#ifdef HAVE_LIBZ
    zlib_stream::zip_istream *zIn;


    if (!CheckedForGzip) {
      zIn = new zlib_stream::zip_istream(*pInStream);
      if (zIn->is_gzip()) {
        pInStream = zIn;
        CheckedForGzip = true;
      }
      else
        delete zIn;
    }
#endif

    InstallStreamFilter();


    obLocale.SetLocale();


    locale originalLocale = pInStream->getloc();
    locale cNumericLocale(originalLocale, "C", locale::numeric);
    pInStream->imbue(cNumericLocale);


    if (!SkippedMolecules) {
        Count = 0;
        if(!SetStartAndEnd()) {
           return false;
        }
        SkippedMolecules = true;
    }


    Count++;
    bool success = false;
    if (EndNumber==0 || Count<=EndNumber) {
        success = pInFormat->ReadMolecule(pOb, this);
    }


    obLocale.RestoreLocale();

    pInStream->imbue(originalLocale);


    if (!success && !pInStream->good() && NeedToFreeInStream) {
      ifstream *inFstream = dynamic_cast<ifstream*>(pInStream);
      if (inFstream != 0)
        inFstream->close();
    }

    return success;
  }
