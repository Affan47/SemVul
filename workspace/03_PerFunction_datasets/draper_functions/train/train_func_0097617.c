GetSpec() const{
	gnGenomeSpec *spec = new gnGenomeSpec();
	for(uint32 i=0; i < m_contigList.size(); i++){

		gnFragmentSpec *fragmentSpec = new gnFragmentSpec();
		gnSourceSpec *contigSpec = new gnSourceSpec((gnBaseSource*)this, i);

		spec->AddSpec(fragmentSpec, i);
		fragmentSpec->AddSpec(contigSpec);

		fragmentSpec->SetName(m_contigList[i]->GetName());
		fragmentSpec->SetSourceName(m_openString);
		contigSpec->SetName(m_contigList[i]->GetName());
		contigSpec->SetSourceName(m_openString);

		pair<uint64,uint64> headsect = m_contigList[i]->GetSectStartEnd(gnContigHeader);
		if(headsect.first != headsect.second){
			gnSourceHeader *gpsh = new gnSourceHeader((gnBaseSource *)this, string(""), headsect.first, headsect.second - headsect.first);
			fragmentSpec->AddHeader(gpsh, 0);
		}
	}
	return spec;
}
