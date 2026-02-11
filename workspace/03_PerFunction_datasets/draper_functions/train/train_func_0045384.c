dumpQueryResult(QueryResult qres)
{
  if( d_translate && d_em->getOutputLang() == SMTLIB_LANG ) {
    *d_osdump << "  :status ";
    switch( qres ) {
    case UNSATISFIABLE:
      *d_osdump << "unsat" << endl;
      break;
    case SATISFIABLE:
      *d_osdump << "sat" << endl;
      break;
    default:
      *d_osdump << "unknown" << endl;
      break;
    }
  } else if( d_translate && d_em->getOutputLang() == SMTLIB_V2_LANG ) {
    *d_osdump << "(set-info :status ";
    switch( qres ) {
    case UNSATISFIABLE:
      *d_osdump << "unsat";
      break;
    case SATISFIABLE:
      *d_osdump << "sat";
      break;
    default:
      *d_osdump << "unknown";
      break;
    }
    *d_osdump << ")" << endl;
  } else if( d_translate && d_em->getOutputLang() == SPASS_LANG ) {
    *d_osdump << "status(";
    switch( qres ) {
    case UNSATISFIABLE:
      *d_osdump << "unsatisfiable";
      break;
    case SATISFIABLE:
      *d_osdump << "satisfiable";
      break;
    default:
      *d_osdump << "unknown";
      break;
    }
    *d_osdump << ")." << endl;
  }
}
