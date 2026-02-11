sqliteInitCallback(void *pInit, int argc, char **argv, char **azColName){
  InitData *pData = (InitData*)pInit;
  int nErr = 0;

  assert( argc==5 );
  if( argv==0 ) return 0;
  if( argv[0]==0 ){
    corruptSchema(pData, 0);
    return 1;
  }
  switch( argv[0][0] ){
    case 'v':
    case 'i':
    case 't': {
      sqlite *db = pData->db;
      if( argv[2]==0 || argv[4]==0 ){
        corruptSchema(pData, 0);
        return 1;
      }
      if( argv[3] && argv[3][0] ){


        char *zErr;
        assert( db->init.busy );
        db->init.iDb = atoi(argv[4]);
        assert( db->init.iDb>=0 && db->init.iDb<db->nDb );
        db->init.newTnum = atoi(argv[2]);
        if( sqlite_exec(db, argv[3], 0, 0, &zErr) ){
          corruptSchema(pData, zErr);
          sqlite_freemem(zErr);
        }
        db->init.iDb = 0;
      }else{


        int iDb;
        Index *pIndex;

        iDb = atoi(argv[4]);
        assert( iDb>=0 && iDb<db->nDb );
        pIndex = sqliteFindIndex(db, argv[1], db->aDb[iDb].zName);
        if( pIndex==0 || pIndex->tnum!=0 ){


          ;
        }else{
          pIndex->tnum = atoi(argv[2]);
        }
      }
      break;
    }
    default: {

      nErr = 1;
      assert( nErr==0 );
    }
  }
  return nErr;
}
