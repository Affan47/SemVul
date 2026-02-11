openSession(const string& inUserName,
					const string& inSessionName){

  CXMLElement* lOpenedSession(mSessionManager.openSession(inUserName,
							  "",
							  inSessionName));

  if(lOpenedSession){
    string lNewID(lOpenedSession->stringReadAttribute(mrml_const::session_id).second);

    cout << mMultiResponse->stringReadAttribute(mrml_const::session_id).second
	 << "-> new Session ID: "
	 << lNewID
	 << endl;

    mMultiResponse->addAttribute(string(mrml_const::session_id),
				 lNewID);
    cout << "current state in multi reponse :"
	 << mMultiResponse->stringReadAttribute(mrml_const::session_id).second
	 << endl;
  }
  addToMultiResponse(lOpenedSession);
}
