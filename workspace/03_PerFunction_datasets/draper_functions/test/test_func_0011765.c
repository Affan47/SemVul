getTiXmlDocument(bool readTrackData, string fitnessDetailId) {
	tcxAuthor->setName("Fit2Tcx");
	TiXmlDocument * output = this->tcxBase->getTcxDocument(readTrackData, fitnessDetailId);
	return output;
}
