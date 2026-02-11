updateNonStandardObjectReferences()
{
    if (getAction() == PolicyRule::Branch)
    {
        RuleSet *branch_ruleset = getBranch();
        setBranch(branch_ruleset);
    }

    if (getTagging())
    {
        FWObject *tag_object = getTagObject();
        setTagObject(tag_object);
    }
}
