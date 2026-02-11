countEpisodes()
    {
        int episodes = 0;
        if (_identityOnly) {
            Form::FormMain *form = formManager().identityRootForm();
            if (form)
                episodes = 1;
        } else {

            QList<Form::FormMain*> forms = formManager().allDuplicatesEmptyRootForms();


            foreach(Form::FormMain *emptyRoot, forms) {
                foreach(Form::FormMain *form, emptyRoot->flattenedFormMainChildren()) {
                    if (form->spec()->value(FormItemSpec::Spec_IsIdentityForm).toBool())
                        continue;
                    EpisodeModel *model = formCore().episodeManager().episodeModel(form);
                    if (model->currentPatientUuid() != patient()->uuid())
                        return 0;

                    QModelIndex fetchIndex = model->index(model->rowCount(), 0);
                    while (model->canFetchMore(fetchIndex)) {
                        model->fetchMore(fetchIndex);
                        fetchIndex = model->index(model->rowCount(), 0);
                    }
                    episodes += model->rowCount();
                }
            }
        }
        return episodes;
    }
