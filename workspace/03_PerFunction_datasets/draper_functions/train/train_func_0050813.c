WriteCandidates(SignalingProtocol protocol,
                                         const Candidates& candidates,
                                         XmlElements* candidate_elems,
                                         WriteError* error) {


  for (std::vector<Candidate>::const_iterator iter = candidates.begin();
       iter != candidates.end(); ++iter) {
    buzz::XmlElement* cand_elem =
        new buzz::XmlElement(GetCandidateQName(protocol));
    if (!WriteCandidate(*iter, cand_elem, error))
      return false;
    candidate_elems->push_back(cand_elem);
  }
  return true;
}
