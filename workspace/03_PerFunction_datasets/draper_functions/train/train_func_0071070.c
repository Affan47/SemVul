free_prompts(prompts_t *p)
{
    size_t i;
    for (i=0; i < p->n_prompts; i++) {
	prompt_t *pr = p->prompts[i];
	memset(pr->result, 0, pr->result_len);
	sfree(pr->result);
	sfree(pr->prompt);
	sfree(pr);
    }
    sfree(p->prompts);
    sfree(p->name);
    sfree(p->instruction);
    sfree(p);
}
