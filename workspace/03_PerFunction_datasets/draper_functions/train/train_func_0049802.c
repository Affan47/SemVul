step_matches(struct step *step, struct tree *tree) {
    return (step->name == NULL || streqx(step->name, tree->label));
}
