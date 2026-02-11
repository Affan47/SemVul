insert_after_entry(AED_area_entry *add_after_this, AED_area_entry *to_be_inserted) {
    if( last == add_after_this )
        last = to_be_inserted;
    to_be_inserted->next                            = add_after_this->next;
    to_be_inserted->previous                    = add_after_this;
    if ( add_after_this->next )
        add_after_this->next->previous      = to_be_inserted;
    add_after_this->next                            = to_be_inserted;

    size++;
    to_be_inserted->in_area = this;
    this->insert_hash(to_be_inserted->ad_species->name());
}
