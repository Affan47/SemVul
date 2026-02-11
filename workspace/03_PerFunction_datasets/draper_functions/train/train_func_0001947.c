Clone(FCDAsset* clone, bool cloneAllContributors) const
{
	if (clone == NULL) clone = new FCDAsset(const_cast<FCDocument*>(GetDocument()));


	clone->creationDateTime = creationDateTime;
	clone->modifiedDateTime = FUDateTime::GetNow();
	clone->keywords = keywords;
	clone->revision = revision;
	clone->subject = subject;
	clone->title = title;
	clone->upAxis = upAxis;
	clone->unitName = unitName;
	clone->unitConversionFactor = unitConversionFactor;
	clone->SetFlag(TestFlag(FLAG_HasUnits | FLAG_HasUpAxis));

	if (cloneAllContributors)
	{

		for (const FCDAssetContributor** it = contributors.begin(); it != contributors.end(); ++it)
		{
			FCDAssetContributor* clonedContributor = clone->AddContributor();
			(*it)->Clone(clonedContributor);
		}
	}

	return clone;
}
