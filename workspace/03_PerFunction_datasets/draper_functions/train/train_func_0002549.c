GetBaseTarget() const
{
	if (skinController != NULL) return skinController->GetTarget();
	else if (morphController != NULL) return morphController->GetBaseTarget();
	else return NULL;
}
