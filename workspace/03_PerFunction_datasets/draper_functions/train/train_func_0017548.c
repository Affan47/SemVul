OutputTranslationOptions(std::ostream &out, ApplicationContext &applicationContext, const ChartHypothesis *hypo, const Sentence &sentence, long translationId)
{

  if (hypo != NULL) {
    ReconstructApplicationContext(*hypo, sentence, applicationContext);
    out << "Trans Opt " << translationId
        << " " << hypo->GetCurrSourceRange()
        << ": ";
    WriteApplicationContext(out, applicationContext);
    out << ": " << hypo->GetCurrTargetPhrase().GetTargetLHS()
        << "->" << hypo->GetCurrTargetPhrase()
        << " " << hypo->GetTotalScore() << hypo->GetScoreBreakdown()
        << endl;
  }

  const std::vector<const ChartHypothesis*> &prevHypos = hypo->GetPrevHypos();
  std::vector<const ChartHypothesis*>::const_iterator iter;
  for (iter = prevHypos.begin(); iter != prevHypos.end(); ++iter) {
    const ChartHypothesis *prevHypo = *iter;
    OutputTranslationOptions(out, applicationContext, prevHypo, sentence, translationId);
  }
}
