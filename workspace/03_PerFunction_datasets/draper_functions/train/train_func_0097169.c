Reporting_records(bool force_resend)
  {
    Arc::XMLNode sendingXMLrecords(Arc::NS("","http://eu-emi.eu/namespaces/2012/11/aggregatedcomputerecord"),
                   "SummaryRecords");

    Arc::XMLNode node = aggregationrecordset["SummaryRecord"];
    while (node) {
      if ( force_resend ) {

        NodeCleaning(sendingXMLrecords.NewChild(node));
        ++node;
        continue;
      }
      Arc::XMLNode lastsendingnode = node["LastSending"];
      std::string lastsending= "";

      while ( lastsendingnode ) {
        lastsending = (std::string)lastsendingnode;
        ++lastsendingnode;
      }

      if ( lastsending < (std::string)node["LastModification"] ) {
        NodeCleaning(sendingXMLrecords.NewChild(node));
      }
      ++node;
    }

    if ( sendingXMLrecords.Size() == 0 ) {
      logger.msg(Arc::INFO, "Does not sending empty aggregation/synch message.");
      return true;
    }

    std::string all_records;
    if (synch_message) {

      all_records = SynchMessage(sendingXMLrecords);
    } else {

      sendingXMLrecords.GetXML(all_records,true);
    }
    Arc::MCC_Status status = send_records(all_records);
    if ( status != Arc::STATUS_OK ) {
      return false;
    }

    UpdateLastSendingDate();

    return save_records();
  }
