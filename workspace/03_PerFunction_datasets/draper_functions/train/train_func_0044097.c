partTitle(const QString & moduleID) {
	ModelPart *mp = retrieveModelPart(moduleID);
	if(mp) {
		return mp->modelPartShared()->title();
	} else {
		return ___emptyString___;
	}
}
