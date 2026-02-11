tracebooleanTopValue() {
    if (singleStepOption) {
        if (top(stack)) printf("\t=TRUE\t");
        else printf("\t=FALSE\t");
    }
}
