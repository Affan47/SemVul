sayPronoun(int instance) {
    if (instances[instance].pronoun != 0)
        output(wordWithCode(PRONOUN_BIT, instances[instance].pronoun));
    else
        sayInheritedPronoun(instances[instance].parent);
}
