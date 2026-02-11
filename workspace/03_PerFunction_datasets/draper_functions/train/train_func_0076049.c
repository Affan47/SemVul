xmlSecTransformRemove(xmlSecTransformPtr transform) {
    xmlSecAssert(xmlSecTransformIsValid(transform));

    if(transform->next != NULL) {
        transform->next->prev = transform->prev;
    }
    if(transform->prev != NULL) {
        transform->prev->next = transform->next;
    }
    transform->next = transform->prev = NULL;
}
