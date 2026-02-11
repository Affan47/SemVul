verifySuccess() const
{

	if(!d->success || d->signers.isEmpty())
		return false;


	for(int n = 0; n < d->signers.count(); ++n)
	{
		if(d->signers[n].identityResult() != SecureMessageSignature::Valid)
			return false;
	}
	return true;
}
