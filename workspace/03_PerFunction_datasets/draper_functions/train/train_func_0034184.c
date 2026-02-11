embDmxScophitMergeInsertThisTargetBoth(const AjPList list,
					      AjPScophit hit1,
					      AjPScophit hit2,
					      AjIList iter)
{
    AjPScophit new;


    if(!hit1 || !hit2 || !list || !iter)
	return ajFalse;


    new = embDmxScophitMerge(hit1, hit2);
    ajDmxScophitTarget(&new);
    ajDmxScophitTarget(&hit1);
    ajDmxScophitTarget(&hit2);
    ajDmxScophitTarget2(&new);
    ajDmxScophitTarget2(&hit1);
    ajDmxScophitTarget2(&hit2);
    ajListIterInsert(iter, (void *) new);

    return ajTrue;
}
