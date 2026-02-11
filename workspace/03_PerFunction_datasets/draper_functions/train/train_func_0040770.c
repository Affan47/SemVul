addIA(SPtr<TAddrIA> ia) {
    if (getIA(ia->getIAID()))
    {
        Log(Debug) << "Unable to add IA (iaid=" << ia->getIAID() << "), such IA already exists." << LogEnd;
	      return;
    }
    IAsLst.append(ia);
}
