createWidget(const QString &name, Form::FormItem *formItem, QWidget *parent)
{
    int id = ::widgetsName.indexOf(name);
    if (id == -1)
        return 0;
    switch (id)
    {
    case ::Type_Form : return new BaseForm(formItem,parent);
    case ::Type_Group : return new BaseGroup(formItem,parent);
    case ::Type_Check : return new BaseCheck(formItem,parent);
    case ::Type_Radio : return new BaseRadio(formItem,parent);
    case ::Type_ShortText : return new BaseSimpleText(formItem,parent,true);
    case ::Type_LongText : return new BaseSimpleText(formItem,parent,false);
    case ::Type_HelpText : return new BaseHelpText(formItem,parent);
    case ::Type_MultiList : return new BaseList(formItem,parent,false);
    case ::Type_UniqueList : return new BaseList(formItem,parent,true);
    case ::Type_EditableList : return new BaseEditableStringList(formItem,parent);
    case ::Type_Combo : return new BaseCombo(formItem,parent);
    case ::Type_Date : return new BaseDate(formItem,parent);
    case ::Type_ModernDate : return new BaseDateCompleterWidget(formItem,parent);
    case ::Type_Spin : return new BaseSpin(formItem,parent);
    case ::Type_DoubleSpin : return new BaseSpin(formItem,parent,true);
    case ::Type_Button : return new BaseButton(formItem,parent);
    case ::Type_DetailsWidget: return new BaseDetailsWidget(formItem, parent);
    case ::Type_Measurement: return new MeasurementWidget(formItem, parent);
    case ::Type_FrenchNSS : return new FrenchSocialNumberFormWidget(formItem,parent);

    case ::Type_ButtonMenuPathItemView : return new ButtonMenuPathItemView(formItem,parent);
    default: return 0;
    }
    return 0;
}
