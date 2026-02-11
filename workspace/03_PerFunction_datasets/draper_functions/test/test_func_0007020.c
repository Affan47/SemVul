delegatemDNSCommunity(string dnsName) {

		clock_t timeStamp1, timeStamp2;
		bool tooMuchTime=false;
		double elapsedTime=0.0;

		satisfiedQuery=false;
		solvedQuery="";
		pendingQuery=dnsName;
		ostringstream temp;

		temp << (int)rand()%1024;
		pendingQueryCode=temp.str();
		cout << "delegatemDNSCommunity: generating random code...ok: code=" << pendingQueryCode << " " << endl;

		ostringstream query;

		query << MDNS_REQUEST << " " << dnsName << " " << pendingQueryCode;
		cout << "delegatemDNSCommunity: entering queryWrapper->send(query.str()): " << query.str() << " " << endl;
		queryWrapper->send(query.str());


		timeStamp1=time(0);
		cout << "delegatemDNSCommunity: entering MDNS_RESPONSES waiting loop. TimeStamp1: " << timeStamp1 << " " << endl;
		while (!satisfiedQuery && !tooMuchTime) {
			timeStamp2=time(0);
			cout << "delegatemDNSCommunity: Waiting MDSN_RESPONSES. TimeStamp2: " << timeStamp2 << ", tooMuchTime: " << tooMuchTime << " " << endl;
			elapsedTime=difftime(timeStamp2, timeStamp1);
			if (elapsedTime>=MDNS_TIMEOUT) {
				tooMuchTime=true;
				if (!satisfiedQuery) solvedQuery="MDNS_TIMEOUT ERROR";
			}
			sleep(1);
		}

		return(solvedQuery);
	}
