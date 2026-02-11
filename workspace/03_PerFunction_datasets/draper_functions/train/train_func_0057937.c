updatePeriod() const
{
    return stringToPeriod(resource()->property(SyndicationVocab::self()->updatePeriod())->asString());
}
