GetScoreRatio() const
{
	return credits ? credits->GetScoreRatio(GetIP(), theApp->CryptoAvailable()) : 0;
}
