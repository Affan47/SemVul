updateAccessControls() {
    setComboContent(d->ownerPermCombo, PermissionsOwner,
                    d->permissions, d->partialPermissions);
    setComboContent(d->groupPermCombo, PermissionsGroup,
                    d->permissions, d->partialPermissions);
    setComboContent(d->othersPermCombo, PermissionsOthers,
                    d->permissions, d->partialPermissions);

    switch(d->pmode) {
    case PermissionsOnlyLinks:
        enableAccessControls(false);
        break;
    case PermissionsOnlyFiles:
        enableAccessControls(d->canChangePermissions && !d->isIrregular && !d->hasExtendedACL);
        if (d->canChangePermissions)
            d->explanationLabel->setText(d->isIrregular || d->hasExtendedACL ?
                                         i18np("This file uses advanced permissions",
                                               "These files use advanced permissions.",
                                               properties->items().count()) : "");
        if (d->partialPermissions & UniExec) {
            d->extraCheckbox->setTristate();
            d->extraCheckbox->setCheckState(Qt::PartiallyChecked);
        }
        else {
            d->extraCheckbox->setTristate(false);
            d->extraCheckbox->setChecked(d->permissions & UniExec);
        }
        break;
    case PermissionsOnlyDirs:
        enableAccessControls(d->canChangePermissions && !d->isIrregular && !d->hasExtendedACL);


        if ( d->cbRecursive )
            d->cbRecursive->setEnabled( d->canChangePermissions && !d->isIrregular );

        if (d->canChangePermissions)
            d->explanationLabel->setText(d->isIrregular || d->hasExtendedACL ?
                                         i18np("This folder uses advanced permissions.",
                                               "These folders use advanced permissions.",
                                               properties->items().count()) : "");
        if (d->partialPermissions & S_ISVTX) {
            d->extraCheckbox->setTristate();
            d->extraCheckbox->setCheckState(Qt::PartiallyChecked);
        }
        else {
            d->extraCheckbox->setTristate(false);
            d->extraCheckbox->setChecked(d->permissions & S_ISVTX);
        }
        break;
    case PermissionsMixed:
        enableAccessControls(d->canChangePermissions && !d->isIrregular && !d->hasExtendedACL);
        if (d->canChangePermissions)
            d->explanationLabel->setText(d->isIrregular || d->hasExtendedACL ?
                                         i18n("These files use advanced permissions.") : "");
        break;
        if (d->partialPermissions & S_ISVTX) {
            d->extraCheckbox->setTristate();
            d->extraCheckbox->setCheckState(Qt::PartiallyChecked);
        }
        else {
            d->extraCheckbox->setTristate(false);
            d->extraCheckbox->setChecked(d->permissions & S_ISVTX);
        }
        break;
    }
}
