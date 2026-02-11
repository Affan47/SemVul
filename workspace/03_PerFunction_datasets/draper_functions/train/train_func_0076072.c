operator<<(raw_ostream &OS,
                                       const ARCInstKind Class) {
  switch (Class) {
  case ARCInstKind::Retain:
    return OS << "ARCInstKind::Retain";
  case ARCInstKind::RetainRV:
    return OS << "ARCInstKind::RetainRV";
  case ARCInstKind::RetainBlock:
    return OS << "ARCInstKind::RetainBlock";
  case ARCInstKind::Release:
    return OS << "ARCInstKind::Release";
  case ARCInstKind::Autorelease:
    return OS << "ARCInstKind::Autorelease";
  case ARCInstKind::AutoreleaseRV:
    return OS << "ARCInstKind::AutoreleaseRV";
  case ARCInstKind::AutoreleasepoolPush:
    return OS << "ARCInstKind::AutoreleasepoolPush";
  case ARCInstKind::AutoreleasepoolPop:
    return OS << "ARCInstKind::AutoreleasepoolPop";
  case ARCInstKind::NoopCast:
    return OS << "ARCInstKind::NoopCast";
  case ARCInstKind::FusedRetainAutorelease:
    return OS << "ARCInstKind::FusedRetainAutorelease";
  case ARCInstKind::FusedRetainAutoreleaseRV:
    return OS << "ARCInstKind::FusedRetainAutoreleaseRV";
  case ARCInstKind::LoadWeakRetained:
    return OS << "ARCInstKind::LoadWeakRetained";
  case ARCInstKind::StoreWeak:
    return OS << "ARCInstKind::StoreWeak";
  case ARCInstKind::InitWeak:
    return OS << "ARCInstKind::InitWeak";
  case ARCInstKind::LoadWeak:
    return OS << "ARCInstKind::LoadWeak";
  case ARCInstKind::MoveWeak:
    return OS << "ARCInstKind::MoveWeak";
  case ARCInstKind::CopyWeak:
    return OS << "ARCInstKind::CopyWeak";
  case ARCInstKind::DestroyWeak:
    return OS << "ARCInstKind::DestroyWeak";
  case ARCInstKind::StoreStrong:
    return OS << "ARCInstKind::StoreStrong";
  case ARCInstKind::CallOrUser:
    return OS << "ARCInstKind::CallOrUser";
  case ARCInstKind::Call:
    return OS << "ARCInstKind::Call";
  case ARCInstKind::User:
    return OS << "ARCInstKind::User";
  case ARCInstKind::IntrinsicUser:
    return OS << "ARCInstKind::IntrinsicUser";
  case ARCInstKind::None:
    return OS << "ARCInstKind::None";
  }
  llvm_unreachable("Unknown instruction class!");
}
