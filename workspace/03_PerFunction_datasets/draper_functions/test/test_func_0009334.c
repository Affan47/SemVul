LabelToAtomicNumber(std::string label)
  {


    labelToZType::const_iterator it;
    it = labelToZ.find( label );
    if ( it != labelToZ.end() ) return it-> second;


    int Z=etab.GetAtomicNum(label.substr(0,2).c_str());


    if (Z==0) Z=etab.GetAtomicNum(label.substr(0,1).c_str());

    if (Z==0){

      errorMsg << "LabelToAtomicNumber got bad Label: " << label << std::endl;
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
    }


    labelToZ.insert( std::pair<std::string,int>(label,Z) );
    return Z;

  }
