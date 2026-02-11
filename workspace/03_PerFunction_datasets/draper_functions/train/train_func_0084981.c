generateInput (Tree sig, const string& idx)
{
	if (fLateq->inputs() == 1) {
		setVectorNameProperty(sig, "x");
		fLateq->addInputSigFormula("x(t)");
		gDocNoticeFlagMap["inputsig"] = true;
		return generateCacheCode(sig, "x(t)");
	} else {
		setVectorNameProperty(sig, subst("x_{$0}", idx));
		fLateq->addInputSigFormula(subst("x_{$0}(t)", idx));
		gDocNoticeFlagMap["inputsigs"] = true;
		return generateCacheCode(sig, subst("x_{$0}(t)", idx));
	}
}
