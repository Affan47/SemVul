phaseForModule(const KService::Ptr& service)
{
    const QVariant phasev = service->property("X-KDE-Kded-phase", QVariant::Int );
    return phasev.isValid() ? phasev.toInt() : 2;
}
