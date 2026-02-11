tauntApply(Unit* pTaunter)
{
    if (HostileReference* ref = iThreatContainer.getReferenceByTarget(pTaunter))
    {
        if (getCurrentVictim() && (ref->getThreat() < getCurrentVictim()->getThreat()))
        {

            if (ref->getTempThreatModifyer() == 0.0f)
            {
                ref->setTempThreat(getCurrentVictim()->getThreat());
            }
        }
    }
}
