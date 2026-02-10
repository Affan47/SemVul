pair() const
    {
      QStringList pair;
      pair.append( mMail->text() );

      switch ( mPolicy->currentIndex() ) {
        case 0:
          pair.append( "ACT_ALWAYS_ACCEPT" );
          break;
        case 1:
          pair.append( "ACT_ALWAYS_REJECT" );
          break;
        case 2:
          pair.append( "ACT_REJECT_IF_CONFLICTS" );
          break;
        case 3:
          pair.append( "ACT_MANUAL_IF_CONFLICTS" );
          break;
        case 4:
          pair.append( "ACT_MANUAL" );
          break;
      }

      return pair;
    }
